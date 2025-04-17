$cppFile = "sort_algorithm_tester.cpp"
$outputExe = "sort_tester.exe"
$logFile = "log.txt"
$generatedDir = "generated_files"

if (Test-Path $logFile) {
    Remove-Item $logFile
}

Write-Host "Compiling $cppFile..."
$compileCommand = "g++ `"$cppFile`" -std=c++17 -o `"$outputExe`""
Invoke-Expression $compileCommand

if (!(Test-Path $outputExe)) {
    Write-Host "Compilation failed." -ForegroundColor Red
    exit 1
}

$binFiles = Get-ChildItem -Path $generatedDir -Recurse -Filter *.bin

if ($binFiles.Count -eq 0) {
    Write-Host "No .bin files found."
    exit 0
}

foreach ($file in $binFiles) {
    $absolutePath = $file.FullName
    Write-Host "Processing file: $absolutePath"

    $startTime = Get-Date
    Start-Process -FilePath $outputExe -ArgumentList "`"$absolutePath`"" -NoNewWindow -RedirectStandardOutput "stdout.tmp" -RedirectStandardError "stderr.tmp" -Wait
    $endTime = Get-Date
    $elapsed = ($endTime - $startTime).TotalSeconds
    $roundedTime = [math]::Round($elapsed, 2)

    $stdout = Get-Content "stdout.tmp" -Raw
    $stderr = Get-Content "stderr.tmp" -Raw
    Remove-Item "stdout.tmp", "stderr.tmp"

    $logEntry = @"
==== File: $absolutePath ====
$stdout
$stderr
Time elapsed: $roundedTime seconds

"@

    Add-Content -Path $logFile -Value $logEntry
}

Write-Host "All tests completed. Output logged to '$logFile'."
