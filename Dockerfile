FROM ubuntu
RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y man
RUN apt-get install -y manpages-dev
RUN apt-get install -y python-pip 
RUN apt-get install -y psmisc
RUN pip install psutil
ADD ./src/ /src
ADD ./do.sh /
RUN /do.sh
