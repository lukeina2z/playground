#!/bin/bash

docker compose -f ./docker-compose-jaeger.yml up --remove-orphans

# --remove-orphans