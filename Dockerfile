FROM php:8.3-cli
RUN apt-get update && apt-get install -y libpq-dev unzip

# extension
RUN docker-php-ext-install pdo pdo_pgsql
WORKDIR /var/www
