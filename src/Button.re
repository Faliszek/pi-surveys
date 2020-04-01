open TW;

let style = ReactDOMRe.Style.make(~transition="0.2s all", ());
[@react.component]
let make = (~onClick, ~children, ~type_=`primary) => {
  let styles =
    switch (type_) {
    | `primary => [
        BorderRadius(RoundedLg),
        BackgroundColor(BgBlue600),
        TextColor(TextWhite),
        BackgroundColor(HoverBgBlue800),
        Padding(Px4),
        Padding(Py3),
      ]
    | `rounded => [
        BackgroundColor(BgRed600),
        Width(W8),
        Height(H8),
        BorderRadius(RoundedFull),
        BackgroundColor(HoverBgRed800),
        TextColor(TextWhite),
        Display(Flex),
        AlignItems(ItemsCenter),
        JustifyContent(JustifyCenter),
        Padding(P0),
      ]
    };
  <button
    onClick
    style
    className={
      [
        Margin(M1),
        FontSize(TextBase),
        BoxShadow(ShadowMd),
        BoxShadow(HoverShadowLg),
        ...styles,
      ]
      ->make
    }>
    children
  </button>;
};