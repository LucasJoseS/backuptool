package config

import (
	"os"
	"time"

	"gopkg.in/yaml.v3"
)

type Config struct {
	BackupRootPath string            `yaml:"backup-root-path"`
	Targets        map[string]string `yaml:"backup"`
	BackupCooldown time.Duration     `yaml:"cooldown"`
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
