module FileText = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?, ~size: int=?) => React.element =
    "FileText";
};

module Results = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?) => React.element = "CheckCircle";
};

module CheckCircle = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?, ~size: int=?) => React.element =
    "CheckCircle";
};

module XCircle = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?) => React.element = "XCircle";
};

module Circle = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?) => React.element = "Circle";
};

module ChevronRight = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?, ~size: int=?) => React.element =
    "ChevronRight";
};

module ChevronLeft = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?, ~size: int=?) => React.element =
    "ChevronLeft";
};

module UserCheck = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?, ~size: int=?) => React.element =
    "UserCheck";
};

module Search = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?, ~size: int=?) => React.element = "Search";
};

module Slash = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?, ~size: int=?) => React.element = "Slash";
};

module LogOut = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?) => React.element = "LogOut";
};

module QuestionMark = {
  [@react.component] [@bs.module "react-feather"]
  external make: (~color: string=?, ~size: int=?) => React.element =
    "HelpCircle";
};