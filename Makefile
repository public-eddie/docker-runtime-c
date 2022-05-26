tag=v0.1.0

image_name=jgkimapp
container_name=jgkimapp

#### docker #####
build-docker:
	docker images | grep none | awk '{print $$3}' | xargs -rn 1 docker rmi -f || true
	docker build -f docker/Dockerfile -t $(image_name):$(tag) .

run-docker:
	docker run --privileged -it -d --shm-size=8G --init --name $(container_name) $(image_name):$(tag)

exec-docker:
	docker exec -it $(container_name) /bin/sh

rm-docker:
	docker stop $(container_name) && docker rm -f $(container_name)
#################

