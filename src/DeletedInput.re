[@react.component]
let make = (~value, ~onChange, ~onDelete) =>
  <Animation.Div
    exit={"opacity": 0.0}
    initial={"opacity": 0.0}
    animate={"opacity": 1.0}
    className=TW.([Display(Flex), AlignItems(ItemsCenter)]->make)>
    <Input
      className=TW.[Margin(Mx4), Margin(My2), Width(TW.W64)]
      value
      onChange
    />
    <Button onClick={_ => onDelete()} type_=`rounded>
      <Text> {j|X|j} </Text>
    </Button>
  </Animation.Div>;