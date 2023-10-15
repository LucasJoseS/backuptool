package config

import (
	"os"

	"gopkg.in/yaml.v3"
)

type Config struct {
	BackupRootPath string            `yaml:"backup-root-path"`
	Targets        map[string]string `yaml:"backup"`
}

func New() Config {
	var config Config
	var config_path = os.Getenv("HOME") + "/.config/backuptool.conf"

	f, err := os.ReadFile(config_path)
	if err != nil {
		panic(err)
	}

	yaml.Unmarshal(f, &config)
	return config
}
