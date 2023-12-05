#!/bin/bash
docker rmi -f school21/miniverter:1.0 && docker build . -t school21/miniverter:1.0 -f Dockerfile&& docker run -it school21/miniverter:1.0
