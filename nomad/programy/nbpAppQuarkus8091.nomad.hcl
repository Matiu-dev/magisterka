 job "nbpapp8091" {
  datacenters = ["dc1"]
  type        = "service"

  group "web" {
    count = 1

    network {
      port "quarkus"
      {
        to = 8091
      }
    }

    task "service" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8091:latest"
        network_mode = "host"
        ports        = ["quarkus"]
      }
    }
  }
}
