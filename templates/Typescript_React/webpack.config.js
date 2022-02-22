const path = require("path");

module.exports = {
  entry: "./src/index.tsx", // where to look for content to be bundled
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        use: "ts-loader", // handle typescript
        exclude: /node_modules/
      }
    ]
  },
  mode: "production",
  resolve: { // how to resolve dependencies
    extensions: [".tsx", ".ts", ".js"]
  },
  output: { // where to write bundle to
    path: path.resolve(__dirname, "dist"),
    filename: "bundle.js"
  },
  devServer: {
    contentBase: path.join(__dirname, "dist"),
    compress: true,
    port: 9000
  }
};