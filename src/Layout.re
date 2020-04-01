open TW;
open Belt;

[@react.component]
let make = (~children) =>
  <div
    className={
      [MinHeight(MinHScreen), Display(Flex), FlexDirection(FlexCol)]->make
    }>
    <div
      className={
        [
          Width(WFull),
          BackgroundColor(BgBlue600),
          Height(H16),
          BoxShadow(ShadowLg),
          Display(Flex),
          AlignItems(ItemsCenter),
        ]
        ->make
      }>
      <Text
        className=[
          Margin(Ml4),
          FontSize(TextXl),
          TextColor(TextWhite),
          FontWeight(FontBold),
        ]>
        "Ankiety"
      </Text>
    </div>
    <main className={[Width(WFull), Flex(Flex1), Display(Flex)]->make}>
      <nav
        className={
          [Width(W64), Padding(Py8), Padding(Px4), BoxShadow(ShadowMd)]
          ->make
        }>
        <ul> <li> <Text> "Ankiety" </Text> </li> </ul>
      </nav>
      <div className={[Width(WFull)]->make}>
        <div className={[Padding(Py8), Padding(Px12)]->make}>
          <div
            className={
              [BorderRadius(Rounded), BoxShadow(ShadowLg), Padding(P8)]
              ->make
            }>
            children
          </div>
        </div>
      </div>
    </main>
  </div>;