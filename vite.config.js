// vite.config.js
import { defineConfig } from "vite";

export default defineConfig({
  // 配置选项
  build: {
    outDir: "dist", // 将打包后的文件输出到 dist 目录
    minify: "eslint", // 使用 terser 进行压缩
    lib: {
      entry: "./main.js",
      name: "Abracadabra",
      fileName: "abracadabra-cn",
    },
  },
});
