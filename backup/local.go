package backup

import (
	"os/exec"
	"path"
)

func LocalBackup(category string, src string, destination string) {
	last := path.Base(src)

	cmd := exec.Command("mkdir", "--parents", destination)
	cmd.Run()

	cmd = exec.Command("cp", "--recursive", "--force", src, destination+"/"+last)
	err := cmd.Run()
	if err != nil {
		panic(err)
	}
}
