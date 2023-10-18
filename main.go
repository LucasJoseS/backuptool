package main

import (
	"fmt"
	"time"

	"github.com/backuptool/backup"
	"github.com/backuptool/cache"
	"github.com/backuptool/config"
)

func main() {
	config := config.New()
	cache := cache.New()

	println("Backup root path: ", config.BackupRootPath)

	timestamp := time.Now()
	for category, path := range config.Targets {
		fmt.Printf("Categoty: %-20s, Target: %s\n", category, path)

		destination := config.BackupRootPath
		destination += fmt.Sprintf("/%v/%s/%v", timestamp.Year(), timestamp.Month().String(), timestamp.Day())

		backup.LocalBackup(category, path, destination)
	}

	for category, path := range config.StaticTargets {
		fmt.Printf("Categoty: % -20s, Static target: %s\n", category, path)

		destination := config.BackupRootPath
		destination += "/Static"

		backup.LocalBackup(category, path, destination)
	}

	cache.UpdateLastBackupTime()
}
