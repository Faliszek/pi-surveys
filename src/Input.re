[@react.component]
let make = (~value, ~onChange) =>
  <input
    type_="text"
    value
    onChange={e => e->ReactEvent.Synthetic.target##value->onChange}
  />;