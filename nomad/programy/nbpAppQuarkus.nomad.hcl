 job "nbpapp" {
  datacenters = ["dc1"]
  type        = "service"

  group "web" {
    count = 1

    network {
      port "quarkus"
      {
        to = 8080
      }
    }

    task "service" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app:latest"
        network_mode = "host"
        ports        = ["quarkus"]
      }
    }
  }
}
