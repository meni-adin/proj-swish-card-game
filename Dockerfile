FROM ubuntu

ARG REPO_NAME=proj-swish-card-game

RUN echo "APT::Get::Assume-Yes \"true\";\nAPT::Get::force-yes \"true\";\n" > /etc/apt/apt.conf

RUN apt update
RUN apt install git
RUN apt install python3
RUN apt install cmake
RUN apt install ninja-build
RUN apt install gcc
RUN apt install g++
RUN apt install valgrind
RUN apt install clang-tidy

WORKDIR /root/
COPY . ${REPO_NAME}

ARG CACHEBUST=1
RUN git clone --depth 1 https://github.com/google/googletest.git _github.com/google/googletest

ENV TERM=xterm-256color
RUN echo "PS1='\e[92m\u\e[0m@\e[94m\h\e[0m:\e[35m\w\e[0m# '" >> /root/.bashrc

WORKDIR /root/${REPO_NAME}
CMD ["python3", "scripts/build_and_test.py"]
