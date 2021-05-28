@REM if [[ "$1" = "gdb" ]]
@REM     qemu-system-x86_64.exe -s -S -hda Image/x64BareBonesImage.qcow2 -m 512 -d int
@REM else
@REM     qemu-system-x86_64.exe -hda Image/x64BareBonesImage.qcow2 -m 512
qemu-system-x86_64.exe -hda Image/x64BareBonesImage.qcow2 -m 512 %*