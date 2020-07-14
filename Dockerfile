# Pull anaconda image https://hub.docker.com/r/continuumio/anaconda/
ARG ANACONDA_IMAGE=continuumio/anaconda3
FROM ${ANACONDA_IMAGE}

LABEL maintainer="mlengineering@c3.ai"

ENV REPOMAN=https://artifacts.c3-e.com/v1/anaconda

# Silence debconf messages
ENV DEBIAN_FRONTEND noninteractive

# Install g++ compiler in order to cythonize
RUN apt-get update && apt-get -y install apt-utils && apt-get -y upgrade && apt-get -y install g++

# Conda build environment
RUN conda install conda-build

# Ensure everything is up-to-date
RUN conda update conda
RUN conda update conda-build

# Add C3 internal channel to install dependencies
RUN conda config --add channels ${REPOMAN}

# Add repoman site
RUN anaconda config --set sites.repoman.url "${REPOMAN}"
# Set repoman to be default site
Run anaconda config --set default_site repoman

# Define working directory mounted from host
VOLUME /src
WORKDIR /src