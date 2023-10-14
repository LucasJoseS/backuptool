package main

import (
	"fmt"
	"os"
	"os/exec"
	"path"
	"time"

	"gopkg.in/yaml.v3"
)

type Config struct {
	BackupRootPath string            `yaml:"backup-root-path"`
	Targets        map[string]string `yaml:"backup"`
}

func newConfig() Config {
	var config Config
	var config_path = os.Getenv("HOME") + "/.config/backuptool.conf"

	f, err := os.ReadFile(config_path)
	if err != nil {
		panic(err)
	}

	yaml.Unmarshal(f, &config)
	return config
}

func localBackup(category string, src string, config Config) {
	time := time.Now()
	last := path.Base(src)
	destination_root := fmt.Sprint(config.BackupRootPath, "/", time.Year(), "/", time.Month().String(), "/", time.Day(), "/", category)

	cmd := exec.Command("mkdir", "--parents", destination_root)
	err := cmd.Run()
	if err != nil {
		panic(err.Error())
	}

	cmd = exec.Command("cp", "--recursive", src, destination_root+"/"+last)
	err = cmd.Run()
	if err != nil {
		panic(err.Error())
	}
}

func main() {
	var config Config = newConfig()

	for category, path := range config.Targets {
		localBackup(category, path, config)
	}
}
