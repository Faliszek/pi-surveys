open TW;

[@react.component]
let make = (~children, ~className=?, ~color=`gray) => {
  let className = className->Belt.Option.getWithDefault([]);
  let color =
    switch (color) {
    | `gray => TextColor(TextGray600)
    | `white => TextColor(TextWhite)
    | `red => TextColor(TextRed600)
    };

  <span className={[color, ...className]->TW.make}>
    children->React.string
  </span>;
};