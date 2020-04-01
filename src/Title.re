[@react.component]
let make = (~index, ~size=`big) => {
  let size =
    switch (size) {
    | `big => TW.Text3xl
    | `small => TW.TextLg
    };

  <h1 className=TW.([FontSize(size)]->make)>
    <Text> "# " </Text>
    <Text>
      {{
         index + 1;
       }
       ->Js.Int.toString}
    </Text>
  </h1>;
};