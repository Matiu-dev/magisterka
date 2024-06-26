job "pgadmin4" {
  datacenters = ["dc1"]
  type = "service"

  group "pgadmin4" {
    count = 1

    task "pgadmin4" {
      driver = "docker"
      config {
        image = "dpage/pgadmin4"
        ports = ["ui"]
        volumes = [
          "local/servers.json:/servers.json",
          "local/servers.passfile:/root/.pgpass"
        ]

      }
      template {
        perms = "600"
        change_mode = "noop"
        destination = "local/servers.passfile"
        data = <<EOH
postgres.service.consul:5432:postgres:postgres:postgres
EOH
      }
      template {
        change_mode = "noop"
        destination = "local/servers.json"
        data = <<EOH
{
  "Servers": {
    "1": {
      "Name": "Local Server",
      "Group": "Server Group 1",
      "Port": "5432",
      "Username": "root",
      "PassFile": "/root/.pgpass",
      "Host": "postgres.service.consul",
      "SSLMode": "disable",
      "MaintenanceDB": "postgres"
    }
  }
}
EOH
      }
      env {
        PGADMIN_DEFAULT_EMAIL="admin@admin.com"
        PGADMIN_DEFAULT_PASSWORD="admin"
        PGADMIN_LISTEN_PORT="5050"
        PGADMIN_CONFIG_ENHANCED_COOKIE_PROTECTION="False"
        PGADMIN_SERVER_JSON_FILE="/servers.json"
      }

logs {
        max_files     = 5
        max_file_size = 15
      }

      resources {
        cpu = 1000
        memory = 1024
      }
      service {
        name = "pgadmin"
        tags = [ "urlprefix-/pgadmin strip=/pgadmin"]
        port = "ui"

        check {
          name     = "alive"
          type     = "tcp"
          interval = "10s"
          timeout  = "2s"
        }
      }
    }
    restart {
      attempts = 10
      interval = "5m"
      delay = "25s"
      mode = "delay"
    }
    network {
      mbits = 10
      port  "ui"  {
        static = 5050
      }
    }
  }

  update {
    max_parallel = 1
    min_healthy_time = "5s"
    healthy_deadline = "3m"
    auto_revert = false
    canary = 0
  }
}
