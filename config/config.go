package config

import (
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
		panic(config_path + " not exists.")
	}

	yaml.Unmarshal(f, &config)
	return config
}
