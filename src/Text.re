[@react.component]
let make = (~children, ~className=?) => {
  let className = className->Belt.Option.getWithDefault([]);

  <span className={className->TW.make}> children->React.string </span>;
};