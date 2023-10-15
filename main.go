package main

import (
	"github.com/backuptool/backup"
	"github.com/backuptool/config"
)

func main() {
	config := config.New()
  println("Backup root path: ", config.BackupRootPath)

	for category, path := range config.Targets {
    println("Target: ", path, " category: ", category)
		backup.LocalBackup(category, path, config)
	}
}
