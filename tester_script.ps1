# File and folder setup
$cppFile = "sort_algorithm_tester.cpp"
$outputExe = "sort_tester.exe"
$logFile = "log.txt"
$generatedDir = "generated_files"

# Clean up previous log
if (Test-Path $logFile) {
    Remove-Item $logFile
}

# Compile the source code
Write-Host "Compiling $cppFile..."
$compileCommand = "g++ `"$cppFile`" -std=c++17 -o `"$outputExe`""
Invoke-Expression $compileCommand

if (!(Test-Path $outputExe)) {
    Write-Host "Compilation failed." -ForegroundColor Red
    exit 1
}

# Find all .bin files
$binFiles = Get-ChildItem -Path $generatedDir -Recurse -Filter *.bin

if ($binFiles.Count -eq 0) {
    Write-Host "No .bin files found."
    exit 0
}

# Use background jobs to run in parallel
$jobs = @()

foreach ($file in $binFiles) {
    $absolutePath = $file.FullName
    $job = Start-Job -ScriptBlock {
        param($exe, $binFile)

        $startTime = Get-Date
        $proc = Start-Process -FilePath $exe -ArgumentList "`"$binFile`"" -NoNewWindow -RedirectStandardOutput "stdout.tmp" -RedirectStandardError "stderr.tmp" -Wait
        $endTime = Get-Date
        $elapsed = ($endTime - $startTime).TotalSeconds
        $roundedTime = [math]::Round($elapsed, 2)

        $stdout = Get-Content "stdout.tmp" -Raw
        $stderr = Get-Content "stderr.tmp" -Raw
        Remove-Item "stdout.tmp", "stderr.tmp"

        return @"
==== File: $binFile ====
$stdout
$stderr
Time elapsed: $roundedTime seconds

"@
    } -ArgumentList (Join-Path $PWD $outputExe), $absolutePath

    $jobs += $job
}

# Wait for all jobs to finish
Write-Host "Waiting for all jobs to complete..."
Wait-Job -Job $jobs

# Collect and write all outputs to log file
foreach ($job in $jobs) {
    $result = Receive-Job -Job $job
    Add-Content -Path $logFile -Value $result
    Remove-Job -Job $job
}

Write-Host "All tests completed. Output logged to '$logFile'."
