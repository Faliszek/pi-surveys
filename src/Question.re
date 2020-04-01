open TW;

[@react.component]
let make = (~index, ~children) =>
  <div className={[Margin(Mb8)]->make}>
    <Title index />
    <div className={[Margin(Ml4)]->make}> children </div>
  </div>;