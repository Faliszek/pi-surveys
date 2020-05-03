open TW;

[@react.component]
let make = (~children, ~className=?, ~color=`gray, ~onClick=_ => ()) => {
  let className = className->Belt.Option.getWithDefault([]);
  let color =
    switch (color) {
    | `gray => TextColor(TextGray600)
    | `light => TextColor(TextGray500)
    | `white => TextColor(TextWhite)
    | `red => TextColor(TextRed600)
    | `blue => TextColor(TextBlue600)
    };

  <span onClick className={[color, ...className]->TW.make}>
    children->React.string
  </span>;
};