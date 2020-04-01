module Presence = {
  [@react.component] [@bs.module "framer-motion"]
  external make:
    (
      ~initial: bool=?,
      ~onExitComplete: unit => unit=?,
      ~children: React.element
    ) =>
    React.element =
    "AnimatePresence";
};

type props = {. "opacity": float};

module Div = {
  [@react.component] [@bs.module "framer-motion"] [@bs.scope "motion"]
  external make:
    (
      ~children: React.element,
      ~exit: props=?,
      ~initial: props=?,
      ~animate: props=?
    ) =>
    React.element =
    "div";
};

module Ul = {
  [@react.component] [@bs.module "framer-motion"] [@bs.scope "motion"]
  external make:
    (
      ~children: React.element,
      ~exit: props=?,
      ~initial: props=?,
      ~animate: props=?
    ) =>
    React.element =
    "ul";
};

module Li = {
  [@react.component] [@bs.module "framer-motion"] [@bs.scope "motion"]
  external make:
    (
      ~children: React.element,
      ~exit: props=?,
      ~initial: props=?,
      ~animate: props=?
    ) =>
    React.element =
    "li";
};