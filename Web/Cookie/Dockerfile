FROM node:13
WORKDIR /app
COPY ./app/package.json /app
RUN npm install
COPY ./app /app
EXPOSE 8080
CMD ["npm", "start"]