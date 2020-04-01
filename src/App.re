open Belt;
open Survey;

let setValue = (questions: array(Question.t), value, id) =>
  questions->Array.map(q => q.id === id ? {...q, value} : q);

let remove = (questions: array(Question.t), id) =>
  questions->Array.keep(q => q.id !== id);

[@react.component]
let make = () => {
  let (questions: array(Question.t), setQuestions) =
    React.useState(() => [||]);

  <div>
    <Animation.Presence>
      {questions
       ->Array.map(q =>
           switch (q.type_) {
           | Open =>
             <DeletedInput
               key={q.id}
               value={q.value}
               onChange={v =>
                 setQuestions(questions => setValue(questions, v, q.id))
               }
               onDelete={() =>
                 setQuestions(questions => remove(questions, q.id))
               }
             />

           | Closed(answers) =>
             <CloseQuestion
               key={q.id}
               value={q.value}
               onChange={v =>
                 setQuestions(questions => setValue(questions, v, q.id))
               }
               onDelete={() =>
                 setQuestions(questions => remove(questions, q.id))
               }
               onChangeAnswer={(answerId, v) =>
                 setQuestions(questions =>
                   Question.changeAnswer(
                     ~questions,
                     ~questionId=q.id,
                     ~answerId,
                     ~value=v,
                   )
                 )
               }
               onAddAnswer={() =>
                 setQuestions(questions =>
                   Question.addAnswer(questions, q.id)
                 )
               }
               onDeleteAnswer={answerId =>
                 setQuestions(questions =>
                   Question.removeAnswer(
                     ~answerId,
                     ~questionId=q.id,
                     questions,
                   )
                 )
               }
               answers
             />
           }
         )
       ->React.array}
    </Animation.Presence>
    <button onClick={_ => setQuestions(Question.add(_, Open))}>
      <Text> {j|Dodaj pytanie otwarte|j} </Text>
    </button>
    <button onClick={_ => setQuestions(Question.add(_, Closed([||])))}>
      <Text> {j|Dodaj pytanie zamknięte|j} </Text>
    </button>
  </div>;
};