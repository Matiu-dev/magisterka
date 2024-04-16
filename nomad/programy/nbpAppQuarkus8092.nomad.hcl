 job "nbpapp8092" {
  datacenters = ["dc1"]
  type        = "service"

  group "web" {
    count = 1

    network {
      port "quarkus"
      {
        to = 8092
      }
    }

    task "service" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8092:latest"
        network_mode = "host"
        ports        = ["quarkus"]
      }
    }
  }
}
