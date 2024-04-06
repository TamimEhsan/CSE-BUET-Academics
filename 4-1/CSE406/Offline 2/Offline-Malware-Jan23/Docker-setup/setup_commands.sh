if [[ "$(docker images -q sshd_tagged_image:latest 2> /dev/null)" == "" ]]; then
  # do something
  sudo docker build -t sshd_tagged_image .
fi

for i in {1..10}; do
docker rm -f test_sshd_container_$i; 
docker run -d -P --name test_sshd_container_$i sshd_tagged_image; 
docker inspect --format='{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' test_sshd_container_$i;
done