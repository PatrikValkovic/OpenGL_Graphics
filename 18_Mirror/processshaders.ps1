$where = $args[0]
$compiler = $args[1]
$output = $args[2]

#Write-Host $where
#Write-Host $compiler
#Write-Host $output

$files = Get-ChildItem $where -Recurse -File
If (-Not (Test-Path $output)){
	New-Item -Path $output -ItemType "directory"
}

foreach($file in $files){
	# $file | Get-Member
	$outputfile = $output + "\" + $file.Name
	# Write-Host $outputfile
	$content = Get-Content $file.FullName
	$content[1..$content.Length] | Out-File "tmp.txt" -Encoding Ascii
	$content[0] | Out-File $outputfile -Encoding Ascii
	& $compiler /EP /C "tmp.txt" | Out-File -Append $outputfile -Encoding Ascii
	Remove-Item -path "tmp.txt"
}