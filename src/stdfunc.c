// # The standard library definitions.
//
// fs:
//   # $fd<|fs.file:
//   #   path: /foo/bar.txt
//   #   truncate: false
//   # $fd.write:
//   #   data: contents of file
//   ~file:
//     args: {path: string, truncate?: bool = false}
//     read:
//       length?: int # if not set, read entire file
//       offset?: int = 0 # default: 0
//       <|: int # number of bytes read
//     write:
//       data: string | bytes
//       length?: int # if not set, read entire file
//       offset?: int = 0
//       <|: int # number of bytes written
//     seek:
//       offset: int # -1 is end of file
//     truncate: {}
//   # fs.read:
//   #   path: /foo/bar.txt
//   read:
//     path: string
//     length?: int # if not set, read entire file
//     offset?: int # default: 0
//     <|: string
//   write:
//     path: string
//     data: string | bytes
//     <|: int # number of bytes written
//   truncate:
//     path: string
//   append:
//     path: string
//     length?: int # if not set, read entire file
//     offset?: int # default: 0
//     <|: int # number of bytes written
//   exists:
//     path: string
//     <|: bool
//   delete:
//     path: string
//     <|: bool
//   .dir:
//     delete:
//       path: string
//     create:
//       path: string
//     chmod:
//       path: string
//     chown:
//       path: string
//
// os:
//   run
//
//
// math:
//   pi
//   abs
//   fabs
//   sqrt
//   log
//   acos
//   asin
//   atan
//   atan2
//   cos
//   cosh
//   sin
//   sinh
//   tanh
//   exp
//
// http:
//   get:
//     url: string
//     params?: map[string, any] # e.g. {a: 123, b: 456}
//     encoding?: string # (json | ...)
//   post:
//     url: string
//     params: map[string, any] # e.g. {a: 123, b: 456}
//     encoding?: string # (json | url)
//   patch:
//     url: string
//     params: map[string, any] # e.g. {a: 123, b: 456}
//     encoding?: string # (json | url)
//   put:
//     url: string
//     params: map[string, any] # e.g. {a: 123, b: 456}
//     encoding?: string # (json | url)
//
