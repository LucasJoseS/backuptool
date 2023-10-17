package backup

import (
	"fmt"
	"os/exec"
	"path"
	"time"

	"github.com/backuptool/config"
)

func LocalBackup(category string, src string, config config.Config) {
	time := time.Now()
	last := path.Base(src)
	destination_root := fmt.Sprint(config.BackupRootPath, "/", time.Year(), "/", time.Month().String(), "/", time.Day(), "/", category)

	cmd := exec.Command("mkdir", "--parents", destination_root)
	cmd.Run()

	cmd = exec.Command("cp", "--recursive", "--force",  src, destination_root+"/"+last)
	err := cmd.Run()
	if err != nil {
		panic(err)
	}
}
