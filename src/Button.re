open TW;

let style = ReactDOMRe.Style.make(~transition="0.2s all", ());

[@react.component]
let make = (~onClick, ~children, ~type_=`primary, ~loading=false, ~htmlType=?) => {
  let styles =
    switch (type_) {
    | `primary => [
        BorderRadius(RoundedLg),
        BackgroundColor(BgBlue400),
        TextColor(TextWhite),
        BackgroundColor(HoverBgBlue500),
        Padding(Px4),
        Padding(Py3),
        TextColor(TextWhite),
      ]

    | `danger => [
        BorderRadius(RoundedLg),
        BackgroundColor(BgRed600),
        TextColor(TextWhite),
        BackgroundColor(HoverBgRed800),
        Padding(Px4),
        Padding(Py3),
        TextColor(TextWhite),
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
        TextColor(TextWhite),
      ]
    };
  <button
    type_={htmlType->Belt.Option.getWithDefault("")}
    onClick
    style
    className={
      [
        Margin(M1),
        FontSize(TextBase),
        BoxShadow(ShadowMd),
        BoxShadow(HoverShadowLg),
        Display(Flex),
        AlignItems(ItemsCenter),
        JustifyContent(JustifyAround),
        ...styles,
      ]
      ->make
    }>
    {loading ? <Loader /> : children}
  </button>;
};