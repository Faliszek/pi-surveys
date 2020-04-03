open TW;

let logo: string = [%bs.raw {|require('./assets/logo.png')|}];

module MenuItem = {
  [@react.component]
  let make = (~icon, ~text) => {
    let active =
      switch (icon) {
      | `survey => true
      | _ => false
      };

    let (textStyle, elStyle, iconColor) =
      active
        ? (
          [TextColor(TextBlue600)],
          [BackgroundColor(BgBlue100)],
          "#3182ce",
        )
        : ([], [], "#718096");

    let iconElement =
      switch (icon) {
      | `result => <Icons.Results color=iconColor />
      | `survey => <Icons.FileText color=iconColor />
      };
    <li>
      <a
        className={
          [
            Margin(My2),
            Padding(Py4),
            Padding(Px4),
            Display(Flex),
            Cursor(CursorPointer),
            TextColor(HoverTextBlue400),
            ...elStyle,
          ]
          ->make
        }>
        iconElement
        <Text className=[Margin(Ml4), FontWeight(FontMedium), ...textStyle]>
          text
        </Text>
      </a>
    </li>;
  };
};

[@react.component]
let make = (~children) =>
  <div
    className={
      [
        MinHeight(MinHScreen),
        Display(Flex),
        FlexDirection(FlexCol),
        BackgroundColor(BgGray100),
      ]
      ->make
    }>
    <div
      className={
        [
          Width(WFull),
          Height(H16),
          BoxShadow(ShadowMd),
          Display(Flex),
          AlignItems(ItemsCenter),
          BackgroundColor(BgWhite),
          ZIndex(Z50),
          Position(Sticky),
          Placement(Top0),
        ]
        ->make
      }>
      <div
        className={
          [Margin(Ml4), Display(Flex), AlignItems(ItemsCenter)]->make
        }>
        <img src=logo className={[Width(W12), Height(H12)]->make} />
        <Text
          className=[
            FontSize(TextXl),
            TextColor(TextWhite),
            FontWeight(FontSemibold),
          ]>
          "UP Ankiety"
        </Text>
      </div>
    </div>
    <main className={[Width(WFull), Flex(Flex1), Display(Flex)]->make}>
      <nav
        className={
          [
            Width(W64),
            Padding(Py8),
            BackgroundColor(BgWhite),
            BoxShadow(ShadowXl),
          ]
          ->make
        }>
        <ul>
          <MenuItem icon=`survey text="Ankiety" />
          <MenuItem icon=`result text="Wyniki" />
        </ul>
      </nav>
      <div className={[Width(WFull)]->make}>
        <div className={[Padding(Py8), Padding(Px12)]->make}>
          <div
            className={
              [
                BorderRadius(RoundedLg),
                BackgroundColor(BgWhite),
                BoxShadow(ShadowXl),
                Padding(P8),
              ]
              ->make
            }>
            children
          </div>
        </div>
      </div>
    </main>
  </div>;