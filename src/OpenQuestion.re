[@react.component]
let make = (~value, ~onChange, ~onDelete, ~index, ~placeholder) =>
  <Question index>
    <DeletedInput value onChange onDelete placeholder />
  </Question>;