package main

import (
	"fmt"

	"github.com/backuptool/backup"
	"github.com/backuptool/cache"
	"github.com/backuptool/config"
)

func main() {
	config := config.New()
	cache := cache.New()

  fmt.Println(config.BackupCooldown)

	println("Backup root path: ", config.BackupRootPath)

	for category, path := range config.Targets {
		println("Target: ", path, " category: ", category)
		backup.LocalBackup(category, path, config)
	}

  cache.UpdateLastBackupTime()
}
