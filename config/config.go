package config

import (
	"fmt"
	"os"

	"gopkg.in/yaml.v3"
)

type Config struct {
	BackupRootPath string            `yaml:"backup-root-path"`
	Targets        map[string]string `yaml:"backup"`
	StaticTargets  map[string]string `yaml:"static-backup"`
}

func New() Config {
	var config Config
	var config_path = os.Getenv("HOME") + "/.config/backuptool.conf"

	f, err := os.ReadFile(config_path)
	if err != nil {
    f, err := os.Create(config_path)
    if err != nil {
      panic("Config file can't be created")

      fmt.Fprintln(f, "# vim: set ft=yaml :")
    }
	}

	yaml.Unmarshal(f, &config)
	return config
}
