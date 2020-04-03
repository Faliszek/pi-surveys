module FileText = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?) => React.element = "FileText";
};

module Results = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?) => React.element = "CheckCircle";
};

module CheckCircle = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?) => React.element = "CheckCircle";
};

module Circle = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?) => React.element = "Circle";
};