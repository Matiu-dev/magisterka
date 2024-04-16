 job "nbpapp8090" {
  datacenters = ["dc1"]
  type        = "service"

  group "web" {
    count = 1

    network {
      port "quarkus8090"
      {
        to = 8090
      }
      port "quarkus8091"
      {
        to = 8091
      }
      port "quarkus8092"
      {
        to = 8092
      }
      port "quarkus8093"
      {
        to = 8093
      }
      port "quarkus8094"
      {
        to = 8094
      }
    }

    task "service8090" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8090:latest"
        network_mode = "host"
        ports        = ["quarkus8090"]
      }
    }

    task "service8091" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8091:latest"
        network_mode = "host"
        ports        = ["quarkus8091"]
      }
    }

    task "service8092" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8092:latest"
        network_mode = "host"
        ports        = ["quarkus8092"]
      }
    }

    task "service8093" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8093:latest"
        network_mode = "host"
        ports        = ["quarkus8093"]
      }
    }

    task "service8094" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8094:latest"
        network_mode = "host"
        ports        = ["quarkus8094"]
      }
    }
  }
}
