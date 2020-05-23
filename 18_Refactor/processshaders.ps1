$where = $args[0]
$compiler = $args[1]
$output = $args[2]

$files = Get-ChildItem $where -Recurse -File
New-Item -Path $output -ItemType "directory"

foreach($file in $files){
	# $file | Get-Member
	$outputfile = $output + "\" + $file.Name
	# Write-Host $outputfile
	$content = Get-Content $file.FullName
	$content[1..$content.Length] | Out-File "tmp.txt"
	$content[0] | Out-File $outputfile
	& $compiler -EP "tmp.txt" | Out-File -Append $outputfile
	Remove-Item -path "tmp.txt"
}