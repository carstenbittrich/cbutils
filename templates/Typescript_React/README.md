# React project with Typescript

## create folder for sources
mkdir src
## create folder for output
mkdir src
## package.json
npm init
## add typescript
npm install typescript --save-dev
## adding tslint
npm install tslint --save-dev
## add react
npm install react react-dom
npm install @types/react @types/react-dom --save-dev
## add dist/index.html
## add src/index.tsx

## adding webpack
npm install webpack webpack-cli --save-dev
## adding webpack web server
npm install webpack webpack-dev-server --save-dev
npm install ts-loader --save-dev
## add webpack.config.js

## adding start and build scripts to package.json:
{
  ...
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
    "start": "webpack serve",
    "build": "webpack --env production"
  },
  ..
}