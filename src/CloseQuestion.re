open Belt;
open Survey;

let deleteAnswer = () => ();

[@react.component]
let make =
    (
      ~value,
      ~onChange,
      ~onDelete,
      ~onAddAnswer,
      ~answers: array(Answer.t),
      ~onDeleteAnswer,
      ~onChangeAnswer,
    ) =>
  <Animation.Div
    exit={"opacity": 0.0} initial={"opacity": 0.0} animate={"opacity": 1.0}>
    <Input onChange value />
    <span onClick={_ => onDelete()}> <Text> {j|❌|j} </Text> </span>
    <Animation.Ul>
      <Animation.Presence>
        {answers
         ->Array.map(a =>
             <Animation.Li
               key={a.id}
               exit={"opacity": 0.0}
               initial={"opacity": 0.0}
               animate={"opacity": 1.0}>
               <DeletedInput
                 value={a.value}
                 onChange={v => onChangeAnswer(a.id, v)}
                 onDelete={_ => onDeleteAnswer(a.id)}
               />
             </Animation.Li>
           )
         ->React.array}
      </Animation.Presence>
    </Animation.Ul>
    <button onClick={_ => onAddAnswer()}>
      <Text> {j|Dodaj odpowiedź|j} </Text>
    </button>
  </Animation.Div>;