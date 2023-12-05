FROM quay.io/school21/alpine:3.13
RUN apk --upgrade add \
    git \
    git-lfs \
    curl \
    jq \
    bash \
 build-base \
    python3 \
    valgrind \
    cppcheck \
 alpine-sdk \
 check \
 clang \
 pcre-dev \
 check-dev
RUN mkdir /test 
COPY . /project
WORKDIR "/project"
# ENTRYPOINT ["/bin/bash","ci-scripts/test.sh"]