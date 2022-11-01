FROM ubuntu:21.10

RUN apt-get update
RUN apt-get install python3 --yes
RUN apt-get install python3-pip --yes
RUN python3 -m pip install --upgrade pip
RUN python3 -m pip install clang-format

WORKDIR "/SDLYogurt/format"
CMD sh format.sh
