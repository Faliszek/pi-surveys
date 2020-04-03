open TW;

[@react.component]
let make = (~children, ~className=?, ~color=`gray) => {
  let className = className->Belt.Option.getWithDefault([]);
  let color =
    switch (color) {
    | `gray => TextColor(TextGray600)
    | `white => TextColor(TextWhite)
    };

  <span className={[color, ...className]->TW.make}>
    children->React.string
  </span>;
};