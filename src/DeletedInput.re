open TW;

[@react.component]
let make = (~value, ~onChange, ~onDelete, ~placeholder) => {
  <Animation.Div
    exit={"opacity": 0.0}
    initial={"opacity": 0.0}
    animate={"opacity": 1.0}
    className={[Display(Flex), AlignItems(ItemsCenter)]->make}>
    <div className={[Position(Relative), Margin(Mx4), Margin(My2)]->make}>
      <Input
        className=TW.[Width(TW.W64)]
        value
        onChange
        placeholder
      />
    </div>
    <Button onClick={_ => onDelete()} type_=`rounded>
      <Text color=`white className=[FontSize(TextXl)]> {j|-|j} </Text>
    </Button>
  </Animation.Div>;
};