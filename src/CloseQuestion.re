open Belt;

[@react.component]
let make =
    (
      ~value,
      ~onChange,
      ~onDelete,
      ~onAddAnswer,
      ~answers: array(Survey.Answer.t),
      ~onDeleteAnswer,
      ~onChangeAnswer,
      ~index,
    ) =>
  <Animation.Div
    exit={"opacity": 0.0}
    initial={"opacity": 0.0}
    animate={"opacity": 1.0}
    className=TW.([Display(Flex), AlignItems(ItemsStart)]->make)>
    <Question index>
      <DeletedInput onChange value onDelete />
      <Animation.Presence>
        <Animation.Ul className=TW.([Margin(Ml16)]->make)>
          {answers
           ->Array.mapWithIndex((index, a) =>
               <Animation.Li
                 key={a.id}
                 exit={"opacity": 0.0}
                 initial={"opacity": 0.0}
                 animate={"opacity": 1.0}
                 className=TW.(
                   [Display(Flex), AlignItems(ItemsCenter)]->make
                 )>
                 <Title index size=`small />
                 <DeletedInput
                   value={a.value}
                   onChange={v => onChangeAnswer(a.id, v)}
                   onDelete={_ => onDeleteAnswer(a.id)}
                 />
               </Animation.Li>
             )
           ->React.array}
        </Animation.Ul>
      </Animation.Presence>
    </Question>
    <Button onClick={_ => onAddAnswer()}>
      <Text> {j|Dodaj odpowiedź|j} </Text>
    </Button>
  </Animation.Div>;