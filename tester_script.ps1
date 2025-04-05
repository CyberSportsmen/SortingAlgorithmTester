# Define file paths
$cppFile = "sort_algorithm_tester.cpp"
$outputExe = "sort_tester.exe"
$logFile = "log.txt"
$generatedDir = "generated_files"

# Remove old log
if (Test-Path $logFile) {
    Remove-Item $logFile
}

# Compile the C++ file
Write-Host "Compiling $cppFile..."
$compileCommand = "g++ `"$cppFile`" -std=c++17 -o `"$outputExe`""
$compileResult = Invoke-Expression $compileCommand

if (!(Test-Path $outputExe)) {
    Write-Host "Compilation failed. Exiting." -ForegroundColor Red
    exit 1
}

# Recursively find all .bin files in generated_files
$binFiles = Get-ChildItem -Path $generatedDir -Recurse -Filter *.bin

if ($binFiles.Count -eq 0) {
    Write-Host "No .bin files found in $generatedDir."
    exit 0
}

# Run the compiled program on each .bin file and log output
foreach ($file in $binFiles) {
    $startTime = Get-Date
    Write-Host "Running on $($file.FullName)..."

    # Run the executable with the .bin file as argument and capture output
    $output = & .\sort_tester.exe $file.FullName

    $endTime = Get-Date
    $elapsed = ($endTime - $startTime).TotalSeconds
    $roundedTime = [math]::Round($elapsed, 2)

    # Log the output and time
    Add-Content -Path $logFile -Value "==== File: $($file.FullName) ===="
    Add-Content -Path $logFile -Value "$output"
    Add-Content -Path $logFile -Value "Time elapsed: $roundedTime seconds"
    Add-Content -Path $logFile -Value "`n"
}

Write-Host "All tests completed. Check '$logFile' for output."
