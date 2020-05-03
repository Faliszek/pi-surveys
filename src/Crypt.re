module SHA512 = {
  type t = {. "toString": [@bs.meth] (unit => string)};

  [@bs.module "crypto-js"] [@bs.val "HmacSHA512"]
  external encrypt: (~message: string, ~key: string) => t;
};