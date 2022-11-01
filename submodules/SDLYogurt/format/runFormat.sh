#!/bin/bash
DOCKER_BUILDKIT=0 docker build -t format $(pwd)/../../SDLYogurt -f $(pwd)/../format/Dockerfile
docker run -v /$(pwd)/..:/SDLYogurt format
