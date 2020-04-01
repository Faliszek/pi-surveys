[@react.component]
let make = (~value, ~onChange, ~onDelete) =>
  <Animation.Div
    exit={"opacity": 0.0} initial={"opacity": 0.0} animate={"opacity": 1.0}>
    <Input value onChange />
    <span onClick={_ => onDelete()}> <Text> {j|❌|j} </Text> </span>
  </Animation.Div>;